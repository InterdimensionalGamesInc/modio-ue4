/*
 *  Copyright (C) 2021 mod.io Pty Ltd. <https://mod.io>
 *
 *  This file is part of the mod.io SDK.
 *
 *  Distributed under the MIT License. (See accompanying file LICENSE or
 *   view online at <https://github.com/modio/modio-sdk/blob/main/LICENSE>)
 *
 */

#ifdef MODIO_SEPARATE_COMPILATION
	#include "modio/core/entities/ModioModInfo.h"
#endif

#include "modio/detail/JsonWrapper.h"
#include "modio/detail/ModioJsonHelpers.h"
namespace Modio
{
	/// @docnone
	void from_json(const nlohmann::json& Json, Modio::Metadata& Metadata)
	{
		Detail::ParseSafe(Json, Metadata.Key, "metakey");
		Detail::ParseSafe(Json, Metadata.Value, "metavalue");
	}

	/// @docnone
	void to_json(nlohmann::json& Json, const Modio::Metadata& Metadata)
	{
		Json = nlohmann::json {{"metakey", Metadata.Key}, {"metavalue", Metadata.Value}};
	}

	/// @docnone
	void from_json(const nlohmann::json& Json, Modio::ModTag& ModTag)
	{
		Detail::ParseSafe(Json, ModTag.Tag, "name");
	}

	/// @docnone
	void to_json(nlohmann::json& Json, const Modio::ModTag& Tag)
	{
		Json = nlohmann::json {{"name", Tag.Tag}};
	}

	/// @docnone
	void from_json(const nlohmann::json& Json, Modio::ModInfo& ModInfo)
	{
		Detail::ParseSafe(Json, ModInfo.ModId, "id");

		{
			Modio::FileMetadata FileInfo;
			if (Detail ::ParseSafe(Json, FileInfo, "modfile"))
			{
				if (FileInfo.ModId == -1)
				{
					// This means that the FileInfo was found in
					// the list of object but did not have a parsable
					// data in the json.
					ModInfo.FileInfo = {};
				}
				else
				{
					ModInfo.FileInfo = FileInfo;
				}
			}

			Detail::ParseSafe(Json, ModInfo.MetadataBlob, "metadata_blob");
			Detail::ParseSafe(Json, ModInfo.MetadataKvp, "metadata_kvp");
			Detail::ParseSafe(Json, ModInfo.Tags, "tags");
		}

		{
			Detail::ParseSafe(Json, ModInfo.ProfileDateAdded, "date_added");
			Detail::ParseSafe(Json, ModInfo.ProfileDateLive, "date_live");
			Detail::ParseSafe(Json, ModInfo.ProfileDateUpdated, "date_updated");
			Detail::ParseSafe(Json, ModInfo.ProfileDescription, "description");
			Detail::ParseSafe(Json, ModInfo.ProfileDescriptionPlaintext, "description_plaintext");
			Detail::ParseSafe(Json, ModInfo.ProfileMaturityOption, "maturity_option");
			Detail::ParseSafe(Json, ModInfo.ProfileName, "name");
			Detail::ParseSafe(Json, ModInfo.ProfileURL, "profile_url");
			Detail::ParseSafe(Json, ModInfo.ProfileSubmittedBy, "submitted_by");
			Detail::ParseSafe(Json, ModInfo.ProfileSummary, "summary");
			Detail::ParseSafe(Json, ModInfo.ModStatus, "status");
			uint8_t Visibility;
			Detail::ParseSafe(Json, Visibility, "visible");
			ModInfo.bVisible = bool(Visibility);
		}

		{
			Detail::ParseSafe(Json, ModInfo.Stats, "stats");
			Detail::ParseSafe(Json, ModInfo.ModLogo, "logo");
		}

		if (Json.contains("media"))
		{
			Detail::ParseSafe(Json.at("media"), ModInfo.YoutubeURLs.GetRawList(), "youtube");
			Detail::ParseSafe(Json.at("media"), ModInfo.SketchfabURLs.GetRawList(), "sketchfab");
			Detail::ParseSafe(Json.at("media"), ModInfo.GalleryImages, "images");
			ModInfo.NumGalleryImages = ModInfo.GalleryImages.Size();
		}
	}

	/// @docnone
	void to_json(nlohmann::json& Json, const Modio::ModInfo& Info)
	{
		Json = nlohmann::json {{"id", Info.ModId},
							   {"metadata_blob", Info.MetadataBlob},
							   {"metadata_kvp", Info.MetadataKvp},
							   {"tags", Info.Tags},
							   {"date_added", Info.ProfileDateAdded},
							   {"date_live", Info.ProfileDateLive},
							   {"date_updated", Info.ProfileDateUpdated},
							   {"description", Info.ProfileDescription},
							   {"description_plaintext", Info.ProfileDescriptionPlaintext},
							   {"maturity_option", Info.ProfileMaturityOption},
							   {"name", Info.ProfileName},
							   {"profile_url", Info.ProfileURL},
							   {"submitted_by", Info.ProfileSubmittedBy},
							   {"summary", Info.ProfileSummary},
							   {"status", Info.ModStatus},
							   {"visible", Info.bVisible ? 1 : 0},
							   {"stats", Info.Stats},
							   {"logo", Info.ModLogo},
							   {"media", nlohmann::json::object({{"youtube", Info.YoutubeURLs.GetRawList()},
																 {"sketchfab", Info.SketchfabURLs.GetRawList()},
																 {"images", Info.GalleryImages}})}};
		if (Info.FileInfo.has_value())
		{
			Json["modfile"] = Info.FileInfo.value();
		}
	}

} // namespace Modio