// Copyright 2023 Hathora, Inc.

#include "HathoraSDKLobbyV3.h"
#include "HathoraSDKModule.h"

FString FHathoraSDKLobbyV3::GetVisibilityString(EHathoraLobbyVisibility Visibility)
{
	FString VisibilityString = UEnum::GetValueAsString(Visibility);
	VisibilityString = VisibilityString.RightChop(VisibilityString.Find("::") + 2).ToLower();

	return VisibilityString;
}

EHathoraLobbyVisibility FHathoraSDKLobbyV3::ParseVisibility(const FString& VisibilityString)
{
	if (VisibilityString == TEXT("private"))
	{
		return EHathoraLobbyVisibility::Private;
	}
	else if (VisibilityString == TEXT("public"))
	{
		return EHathoraLobbyVisibility::Public;
	}
	else if (VisibilityString == TEXT("local"))
	{
		return EHathoraLobbyVisibility::Local;
	}
	else
	{
		UE_LOG(LogHathoraSDK, Error, TEXT("[ParseVisibility] Unknown visibility: %s"), *VisibilityString);
		return EHathoraLobbyVisibility::Unknown;
	}
}

FHathoraLobbyInfo FHathoraSDKLobbyV3::ParseLobbyInfo(TSharedPtr<FJsonObject> LobbyInfoJson)
{
	FHathoraLobbyInfo LobbyInfo;

	LobbyInfo.ShortCode = LobbyInfoJson->GetStringField(TEXT("shortCode"));

	FDateTime::ParseIso8601(
		*LobbyInfoJson->GetStringField(TEXT("createdAt")),
		LobbyInfo.CreatedAt
	);

	LobbyInfo.CreatedBy = LobbyInfoJson->GetStringField(TEXT("createdBy"));

	// roomConfig can be null; this will keep it empty if it is
	LobbyInfoJson->TryGetStringField(TEXT("roomConfig"), LobbyInfo.RoomConfig);

	LobbyInfo.Visibility = ParseVisibility(LobbyInfoJson->GetStringField(TEXT("visibility")));

	LobbyInfo.Region = ParseRegion(LobbyInfoJson->GetStringField(TEXT("region")));

	LobbyInfo.RoomId = LobbyInfoJson->GetStringField(TEXT("roomId"));
	LobbyInfo.AppId = LobbyInfoJson->GetStringField(TEXT("appId"));

	return LobbyInfo;
}

FHathoraSDKLobbyV3* FHathoraSDKLobbyV3::Instance()
{
	static FHathoraSDKLobbyV3 lobbyV3;
	return &lobbyV3;
}

void FHathoraSDKLobbyV3::CreateLobby(
	EHathoraLobbyVisibility Visibility,
	FString RoomConfig,
	EHathoraCloudRegion Region,
	FString ShortCode,
	FString RoomId,
	FHathoraOnLobbyInfo OnComplete)
{
	TArray<TPair<FString, FString>> QueryOptions;
	if (ShortCode.Len() > 0)
	{
		QueryOptions.Add(TPair<FString, FString>(TEXT("shortCode"), ShortCode));
	}
	if (RoomId.Len() > 0)
	{
		QueryOptions.Add(TPair<FString, FString>(TEXT("roomId"), RoomId));
	}

	FJsonObject Body;
	Body.SetStringField(TEXT("visibility"), GetVisibilityString(Visibility));
	Body.SetStringField(TEXT("roomConfig"), RoomConfig);
	Body.SetStringField(TEXT("region"), GetRegionString(Region));

	SendRequest(
		TEXT("POST"),
		FString::Printf(TEXT("/lobby/v3/%s/create"), *AppId),
		QueryOptions,
		Body,
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraLobbyInfoResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				FString Content = Response->GetContentAsString();

				if (Result.StatusCode == 201)
				{
					TSharedPtr<FJsonObject> OutObject;
					TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
					FJsonSerializer::Deserialize(Reader, OutObject);

					if (OutObject.IsValid())
					{
						Result.Data = ParseLobbyInfo(OutObject);
					}
					else
					{
						Result.ErrorMessage = TEXT("Could not parse response");
					}
				}
				else
				{
					Result.ErrorMessage = Content;
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not create lobby, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[CreateLobby] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[CreateLobby] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKLobbyV3::ListAllActivePublicLobbies(FHathoraOnLobbyInfos OnComplete)
{
	TArray<TPair<FString, FString>> QueryOptions;
	ListActivePublicLobbies(QueryOptions, OnComplete);
}

void FHathoraSDKLobbyV3::ListRegionActivePublicLobbies(EHathoraCloudRegion Region, FHathoraOnLobbyInfos OnComplete)
{
	TArray<TPair<FString, FString>> QueryOptions;
	QueryOptions.Add(TPair<FString, FString>(TEXT("region"), GetRegionString(Region)));
	ListActivePublicLobbies(QueryOptions, OnComplete);
}

void FHathoraSDKLobbyV3::ListActivePublicLobbies(TArray<TPair<FString, FString>> QueryOptions, FHathoraOnLobbyInfos OnComplete)
{
	SendRequest(
		TEXT("GET"),
		FString::Printf(TEXT("/lobby/v3/%s/list/public"), *AppId),
		QueryOptions,
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraLobbyInfosResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				FString Content = Response->GetContentAsString();

				if (Result.StatusCode == 200)
				{
					TArray<TSharedPtr<FJsonValue>> OutArray;
					TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
					FJsonSerializer::Deserialize(Reader, OutArray);

					for (TSharedPtr<FJsonValue> Value : OutArray)
					{
						TSharedPtr<FJsonObject> Object = Value->AsObject();
						Result.Data.Add(ParseLobbyInfo(Object));
					}
				}
				else
				{
					Result.ErrorMessage = Content;
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not list active public lobbies, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[ListActivePublicLobbies] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[ListActivePublicLobbies] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKLobbyV3::GetLobbyInfoByRoomId(FString RoomId, FHathoraOnLobbyInfo OnComplete)
{
	SendRequest(
		TEXT("GET"),
		FString::Printf(TEXT("/lobby/v3/%s/info/roomid/%s"), *AppId, *RoomId),
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraLobbyInfoResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				FString Content = Response->GetContentAsString();

				if (Result.StatusCode == 200)
				{
					TSharedPtr<FJsonObject> OutObject;
					TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
					FJsonSerializer::Deserialize(Reader, OutObject);

					if (OutObject.IsValid())
					{
						Result.Data = ParseLobbyInfo(OutObject);
					}
					else
					{
						Result.ErrorMessage = TEXT("Could not parse response");
					}
				}
				else
				{
					Result.ErrorMessage = Content;
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not get lobby info, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[GetLobbyInfoByRoomId] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[GetLobbyInfoByRoomId] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKLobbyV3::GetLobbyInfoByShortCode(FString ShortCode, FHathoraOnLobbyInfo OnComplete)
{
	SendRequest(
		TEXT("GET"),
		FString::Printf(TEXT("/lobby/v3/%s/info/shortcode/%s"), *AppId, *ShortCode),
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraLobbyInfoResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				FString Content = Response->GetContentAsString();

				if (Result.StatusCode == 200)
				{
					TSharedPtr<FJsonObject> OutObject;
					TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Content);
					FJsonSerializer::Deserialize(Reader, OutObject);

					if (OutObject.IsValid())
					{
						Result.Data = ParseLobbyInfo(OutObject);
					}
					else
					{
						Result.ErrorMessage = TEXT("Could not parse response");
					}
				}
				else
				{
					Result.ErrorMessage = Content;
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not get lobby info, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[GetLobbyInfoByShortCode] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[GetLobbyInfoByShortCode] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}