// Copyright 2023 Hathora, Inc.

#include "HathoraSDKRoomV2.h"
#include "HathoraSDKModule.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonSerializer.h"

FHathoraSDKRoomV2* FHathoraSDKRoomV2::Instance()
{
	static FHathoraSDKRoomV2 roomV2;
	return &roomV2;
}

void FHathoraSDKRoomV2::CreateRoom(EHathoraCloudRegion Region, FString RoomConfig, FString RoomId, FHathoraOnRoomConnectionInfo OnComplete)
{
	FString RegionString = GetRegionString(Region);

	TArray<TPair<FString, FString>> QueryOptions;
	if (RoomId.Len() > 0)
	{
		QueryOptions.Add(TPair<FString, FString>(TEXT("roomId"), RoomId));
	}

	FJsonObject Body;
	Body.SetStringField(TEXT("region"), RegionString);
	if (RoomConfig.Len() > 0)
	{
		Body.SetStringField(TEXT("roomConfig"), RoomConfig);
	}

	SendRequest(
		TEXT("POST"),
		FString::Printf(TEXT("/rooms/v2/%s/create"), *AppId),
		QueryOptions,
		Body,
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraRoomConnectionInfoResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				FString Content = Response->GetContentAsString();

				if (Result.StatusCode == 201)
				{
					FJsonObjectConverter::JsonObjectStringToUStruct(Content, &Result.Data, 0, 0);
				}
				else
				{
					Result.ErrorMessage = Content;
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not create room, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[CreateRoom] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[CreateRoom] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

FHathoraAllocation FHathoraSDKRoomV2::ParseAllocation(const TSharedPtr<FJsonObject>& AllocationJson)
{
	FHathoraAllocation Allocation;

	FString UnscheduledAt;
	AllocationJson->TryGetStringField(TEXT("unscheduledAt"), UnscheduledAt);

	Allocation.bUnscheduled = UnscheduledAt.Len() > 0;
	if (Allocation.bUnscheduled)
	{
		FDateTime::ParseIso8601(*UnscheduledAt, Allocation.UnscheduledAt);
	}

	FDateTime::ParseIso8601(
		*AllocationJson->GetStringField(TEXT("scheduledAt")),
		Allocation.ScheduledAt
	);

	Allocation.ProcessId = AllocationJson->GetStringField(TEXT("processId"));

	Allocation.RoomAllocationId = AllocationJson->GetStringField(TEXT("roomAllocationId"));

	return Allocation;
}

EHathoraRoomStatus FHathoraSDKRoomV2::ParseRoomStatus(const FString& Status)
{
	if (Status == TEXT("scheduling"))
	{
		return EHathoraRoomStatus::Scheduling;
	}
	else if (Status == TEXT("active"))
	{
		return EHathoraRoomStatus::Active;
	}
	else if (Status == TEXT("suspended"))
	{
		return EHathoraRoomStatus::Suspended;
	}
	else if (Status == TEXT("destroyed"))
	{
		return EHathoraRoomStatus::Destroyed;
	}
	else
	{
		return EHathoraRoomStatus::Unknown;
	}
}

void FHathoraSDKRoomV2::GetRoomInfo(FString RoomId, FHathoraOnGetRoomInfo OnComplete)
{
	SendRequest(
		TEXT("GET"),
		FString::Printf(TEXT("/rooms/v2/%s/info/%s"), *AppId, *RoomId),
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraGetRoomInfoResult Result;
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
						TSharedPtr<FJsonValue> CurrentAllocation = OutObject->TryGetField(TEXT("currentAllocation"));
						if (CurrentAllocation.IsValid() && !CurrentAllocation->IsNull())
						{
							Result.Data.CurrentAllocation = ParseAllocation(CurrentAllocation->AsObject());
						}

						Result.Data.Status = ParseRoomStatus(OutObject->GetStringField(TEXT("status")));

						TArray<TSharedPtr<FJsonValue>> Allocations = OutObject->GetArrayField(TEXT("allocations"));
						for (TSharedPtr<FJsonValue> Allocation : Allocations)
						{
							Result.Data.Allocations.Add(ParseAllocation(Allocation->AsObject()));
						}

						// roomConfig can be null; this will keep it empty if it is
						OutObject->TryGetStringField(TEXT("roomConfig"), Result.Data.RoomConfig);

						Result.Data.RoomId = OutObject->GetStringField(TEXT("roomId"));
						Result.Data.AppId = OutObject->GetStringField(TEXT("appId"));
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
				Result.ErrorMessage = TEXT("Could not get room info, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[GetRoomInfo] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[GetRoomInfo] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKRoomV2::GetActiveRoomsForProcess(FString ProcessId, FHathoraOnGetRoomsForProcess OnComplete)
{
	GetRoomsForProcess(ProcessId, true, OnComplete);
}

void FHathoraSDKRoomV2::GetInactiveRoomsForProcess(FString ProcessId, FHathoraOnGetRoomsForProcess OnComplete)
{
	GetRoomsForProcess(ProcessId, false, OnComplete);
}

void FHathoraSDKRoomV2::GetRoomsForProcess(FString ProcessId, bool bActive, FHathoraOnGetRoomsForProcess OnComplete)
{
	SendRequest(
		TEXT("GET"),
		FString::Printf(TEXT("/rooms/v2/%s/list/%s/%s"), *AppId, *ProcessId, bActive ? TEXT("active") : TEXT("inactive")),
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraGetRoomsForProcessResult Result;
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
						FHathoraProcessRoomInfo RoomInfo;

						TSharedPtr<FJsonValue> CurrentAllocation = Object->TryGetField(TEXT("currentAllocation"));
						if (CurrentAllocation.IsValid() && !CurrentAllocation->IsNull())
						{
							RoomInfo.CurrentAllocation = ParseAllocation(CurrentAllocation->AsObject());
						}

						RoomInfo.Status = ParseRoomStatus(Object->GetStringField(TEXT("status")));

						// roomConfig can be null; this will keep it empty if it is
						Object->TryGetStringField(TEXT("roomConfig"), RoomInfo.RoomConfig);

						RoomInfo.RoomId = Object->GetStringField(TEXT("roomId"));
						RoomInfo.AppId = Object->GetStringField(TEXT("appId"));

						Result.Data.Add(RoomInfo);
					}
				}
				else
				{
					Result.ErrorMessage = Content;
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not get active rooms for process, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[GetActiveRoomsForProcess] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[GetActiveRoomsForProcess] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKRoomV2::DestroyRoom(FString RoomId, FHathoraOnDestroyRoom OnComplete)
{
	SendRequest(
		TEXT("POST"),
		FString::Printf(TEXT("/rooms/v2/%s/destroy/%s"), *AppId, *RoomId),
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraDestroyRoomResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				Result.bDestroyed = Result.StatusCode == 204;

				if (!Result.bDestroyed)
				{
					Result.ErrorMessage = Response->GetContentAsString();
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not destroy room, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[DestroyRoom] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[DestroyRoom] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKRoomV2::SuspendRoom(FString RoomId, FHathoraOnSuspendRoom OnComplete)
{
	SendRequest(
		TEXT("POST"),
		FString::Printf(TEXT("/rooms/v2/%s/suspend/%s"), *AppId, *RoomId),
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraSuspendRoomResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				Result.bSuspended = Result.StatusCode == 204;

				if (!Result.bSuspended)
				{
					Result.ErrorMessage = Response->GetContentAsString();
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not suspend room, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[SuspendRoom] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[SuspendRoom] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKRoomV2::GetConnectionInfo(FString RoomId, FHathoraOnRoomConnectionInfo OnComplete)
{
	SendRequest(
		TEXT("GET"),
		FString::Printf(TEXT("/rooms/v2/%s/connectioninfo/%s"), *AppId, *RoomId),
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraRoomConnectionInfoResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				FString Content = Response->GetContentAsString();

				if (Result.StatusCode == 200)
				{
					FJsonObjectConverter::JsonObjectStringToUStruct(Content, &Result.Data, 0, 0);
				}
				else
				{
					Result.ErrorMessage = Content;
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not get connection info, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[GetConnectionInfo] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[GetConnectionInfo] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}

void FHathoraSDKRoomV2::UpdateRoomConfig(FString RoomId, FString RoomConfig, FHathoraOnUpdateRoomConfig OnComplete)
{
	FJsonObject Body;
	Body.SetStringField(TEXT("roomConfig"), RoomConfig);

	SendRequest(
		TEXT("POST"),
		FString::Printf(TEXT("/rooms/v2/%s/update/%s"), *AppId, *RoomId),
		Body,
		[&, OnComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess) mutable
		{
			FHathoraUpdateRoomConfigResult Result;
			if (bSuccess && Response.IsValid())
			{
				Result.StatusCode = Response->GetResponseCode();
				Result.bUpdated = Result.StatusCode == 204;

				if (!Result.bUpdated)
				{
					Result.ErrorMessage = Response->GetContentAsString();
				}
			}
			else
			{
				Result.ErrorMessage = TEXT("Could not update room config, unknown error");
			}

			if (!Result.ErrorMessage.IsEmpty())
			{
				UE_LOG(LogHathoraSDK, Error, TEXT("[UpdateRoomConfig] Error: %s"), *Result.ErrorMessage);
			}

			if (!OnComplete.ExecuteIfBound(Result))
			{
				UE_LOG(LogHathoraSDK, Warning, TEXT("[UpdateRoomConfig] function pointer was not valid, so OnComplete will not be called"));
			}
		});
}