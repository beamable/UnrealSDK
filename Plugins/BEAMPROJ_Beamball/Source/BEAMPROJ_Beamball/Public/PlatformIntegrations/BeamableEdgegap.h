// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "Http.h"
#include "HttpModule.h"

#include "BeamableEdgegap.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BEAMPROJ_BEAMBALL_API UBeamableEdgegap : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamableEdgegap* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamableEdgegap>(); }

	/**
	 * Get geolocation for edgegap management of server deployment.
	 */
	UFUNCTION(BlueprintCallable)
	FBeamOperationHandle UpdateGeolocationStatOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
	{
		auto OperationHandler = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);

		FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

		Request->SetURL("http://ip-api.com/json/");
		Request->SetVerb("GET");

		Request->OnProcessRequestComplete().BindLambda(
			[UserSlot, this, OperationHandler](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
			{
				if (!bSuccess) return;

				FString Json = Response->GetContentAsString();
				// UE_LOG(LogTemp, Log, TEXT("%s"), *Json);
				TSharedPtr<FJsonObject> Obj;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);

				if (FJsonSerializer::Deserialize(Reader, Obj))
				{
					float Lat;
					Obj->TryGetNumberField(TEXT("lat"), Lat);
					float Lon;
					Obj->TryGetNumberField(TEXT("lon"), Lon);

					GetWorld()->GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>()->CPP_SetStatOperation(UserSlot, "beam.edgegap.location", FString::Printf(TEXT("%f;%f"), Lat, Lon),
					                                                                                         FBeamOperationEventHandlerCode::CreateLambda([OperationHandler, this](const FBeamOperationEvent& Event)
					                                                                                         {
						                                                                                         if (Event.EventType == OET_SUCCESS)
						                                                                                         {
							                                                                                         Runtime->RequestTrackerSystem->TriggerOperationSuccess(
								                                                                                         OperationHandler, "Successfully updated location stat");
						                                                                                         }
						                                                                                         else
						                                                                                         {
							                                                                                         Runtime->RequestTrackerSystem->TriggerOperationError(
								                                                                                         OperationHandler, "Error on updated location stat");
						                                                                                         }
					                                                                                         }));
				}
			});

		Request->ProcessRequest();

		return OperationHandler;
	}

	/**
	 * @copydoc UpdateGeolocationStatOperation
	*/
	FBeamOperationHandle CPP_RefreshPingsOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
	{
		auto OperationHandler = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		
		FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

		Request->SetURL("http://ip-api.com/json/");
		Request->SetVerb("GET");

		Request->OnProcessRequestComplete().BindLambda(
			[UserSlot, this, OperationHandler](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bSuccess)
			{
				if (!bSuccess) return;

				FString Json = Response->GetContentAsString();
				// UE_LOG(LogTemp, Log, TEXT("%s"), *Json);
				TSharedPtr<FJsonObject> Obj;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);

				if (FJsonSerializer::Deserialize(Reader, Obj))
				{
					float Lat;
					Obj->TryGetNumberField(TEXT("lat"), Lat);
					float Lon;
					Obj->TryGetNumberField(TEXT("lon"), Lon);

					GetWorld()->GetGameInstance()->GetSubsystem<UBeamStatsSubsystem>()->CPP_SetStatOperation(UserSlot, "beam.edgegap.location", FString::Printf(TEXT("%f;%f"), Lat, Lon),
					                                                                                         FBeamOperationEventHandlerCode::CreateLambda([OperationHandler, this](const FBeamOperationEvent& Event)
					                                                                                         {
						                                                                                         if (Event.EventType == OET_SUCCESS)
						                                                                                         {
							                                                                                         Runtime->RequestTrackerSystem->TriggerOperationSuccess(
								                                                                                         OperationHandler, "Successfully updated location stat");
						                                                                                         }
						                                                                                         else
						                                                                                         {
							                                                                                         Runtime->RequestTrackerSystem->TriggerOperationError(
								                                                                                         OperationHandler, "Error on updated location stat");
						                                                                                         }
					                                                                                         }));
				}
			});

		Request->ProcessRequest();

		return OperationHandler;
	}
};
