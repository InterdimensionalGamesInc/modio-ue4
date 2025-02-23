/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io UE4 Plugin.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-ue4/blob/main/LICENSE>)
 *
 */

using UnrealBuildTool;
using System.IO;
using System.Collections.Generic;

public class uring : ModuleRules
{
	public uring(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        string GeneratedSourcePath = Path.Combine(ModuleDirectory, "Private", "GeneratedSource");
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        PublicIncludePaths.AddRange(new string[] {Path.Combine(ModuleDirectory, "Public"), Path.Combine(ModuleDirectory, "../ThirdParty/liburing/src/include")});
		PrivateIncludePaths.AddRange(new string[] {Path.Combine(GeneratedSourcePath), Path.Combine(ModuleDirectory, "../ThirdParty/liburing/src")});
        PrivateDefinitions.Add("LIBURING_INTERNAL=1");
        if (File.Exists(Path.Combine(ModuleDirectory, "../ThirdParty/liburing/.git")) || Directory.Exists(Path.Combine(ModuleDirectory, "../ThirdParty/liburing/.git")))
        {
            // Clean the generated source directory
            if (Directory.Exists(GeneratedSourcePath))
            {
                Directory.Delete(GeneratedSourcePath, true);
            }
            Directory.CreateDirectory(GeneratedSourcePath); 

            {
                List<string> CFiles = new List<string>(Directory.GetFiles(Path.Combine(ModuleDirectory, "../ThirdParty/liburing/src"), "*.c", SearchOption.AllDirectories));

                foreach (string CFile in CFiles)
                {
                    //Add the original file in our upstream repository as a dependency, so if a user edits it we will copy it over
                    ExternalDependencies.Add(CFile);
                    string DestinationPath = Path.Combine(GeneratedSourcePath, Path.GetFileName(CFile));
                    File.Copy(CFile, DestinationPath, true);
                }

                if (File.Exists(Path.Combine(GeneratedSourcePath,"nolibc.c")))
                {
                    File.Delete(Path.Combine(GeneratedSourcePath, "nolibc.c"));
                }
            }
            {
                string CompatHeader;
                if (Target.Platform == UnrealTargetPlatform.Android)
                {
                    CompatHeader = @"/* SPDX-License-Identifier: MIT */
#ifndef LIBURING_COMPAT_H
#define LIBURING_COMPAT_H

#include <stdint.h>
#include <endian.h>

# include <inttypes.h>

    struct open_how
    {
        uint64_t flags;
        uint64_t mode;
        uint64_t resolve;
    };

#ifndef __kernel_rwf_t
    typedef int __kernel_rwf_t;
#endif

#endif
";
                }
                else
                {
                    CompatHeader = @"/* SPDX-License-Identifier: MIT */
#ifndef LIBURING_COMPAT_H
#define LIBURING_COMPAT_H

#include <stdint.h>
#include <endian.h>

struct __kernel_timespec
    {
        int64_t tv_sec;
        long long tv_nsec;
    };

# include <inttypes.h>

    struct open_how
    {
        uint64_t flags;
        uint64_t mode;
        uint64_t resolve;
    };

#ifndef __kernel_rwf_t
    typedef int __kernel_rwf_t;
#endif

#endif
";
                }
                string CompatHeaderPath = Path.Combine(ModuleDirectory, "Public", "liburing");
                Directory.CreateDirectory(CompatHeaderPath);
                File.WriteAllText(Path.Combine(CompatHeaderPath, "compat.h"), CompatHeader);
            }
        }
    }
}