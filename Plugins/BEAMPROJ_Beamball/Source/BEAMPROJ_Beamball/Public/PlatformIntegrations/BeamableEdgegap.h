// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "Http.h"
#include "HttpModule.h"
#include "AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "AutoGen/SubSystems/BeamballMs/BeamballMsSetEdgegapLocationRequest.h"

#include "BeamableEdgegap.generated.h"

/**
 * On edgegap you required to pass the geolocation of the player to be able to manage the server deployment and make sure players are connecting to the closest server. This subsystem is responsible for getting the geolocation of the player and updating it in the stats subsystem, so it can be used for edgegap management.
 * We use a free API to get the geolocation from the IP address, as we don't need a very accurate location for this purpose, just an approximate location.
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
	 * That is mainly used to update the "beam.edgegap.location" stat, which is used by edgegap to manage the server deployment and make sure players are connecting to the closest server.
	 */
	UFUNCTION(BlueprintCallable)
	FBeamOperationHandle UpdateGeolocationStatOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent)
	{
		auto OperationHandler = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);

		FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
		// We use that API to get to location from IP, as it's a free and simple API that doesn't require an API key. We just need to get an approximate location for server purposes, so it's good enough for our use case.
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


					UBeamballMsSetEdgegapLocationRequest* RequestObject = UBeamballMsSetEdgegapLocationRequest::Make(Lat, Lon, this, {});

					FBeamRequestContext Ctx;

					auto RequestOperation = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), {});

					// We are calling the microservice directly here, because the stats api only accept set stat operations for client public type.
					// And to keep the privacy of the location we set it as a private stat.
					GEngine->GetEngineSubsystem<UBeamBeamballMsApi>()->CPP_SetEdgegapLocation(UserSlot, RequestObject, FOnBeamballMsSetEdgegapLocationFullResponse::CreateLambda(
						                                                                          [OperationHandler, this](FBeamballMsSetEdgegapLocationFullResponse Event)
						                                                                          {
							                                                                          if (Event.State == EBeamFullResponseState::RS_Retrying)
								                                                                          return;

							                                                                          if (Event.State == RS_Success)
							                                                                          {
								                                                                          Runtime->RequestTrackerSystem->TriggerOperationSuccess(
									                                                                          OperationHandler, "Successfully updated location stat");
							                                                                          }
							                                                                          else
							                                                                          {
								                                                                          Runtime->RequestTrackerSystem->TriggerOperationError(
									                                                                          OperationHandler, "Error on updated location stat");
							                                                                          }
						                                                                          }), Ctx, RequestOperation, this);
				}
			});

		Request->ProcessRequest();

		return OperationHandler;
	}

	/**
	 * @copydoc UpdateGeolocationStatOperation
	*/
	FBeamOperationHandle CPP_UpdateGeolocationStatOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent)
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

					UBeamballMsSetEdgegapLocationRequest* RequestObject = UBeamballMsSetEdgegapLocationRequest::Make(Lat, Lon, this, {});

					FBeamRequestContext Ctx;

					auto RequestOperation = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), {});

					// We are calling the microservice directly here, because the stats api only accept set stat operations for client public type.
					// And to keep the privacy of the location we set it as a private stat.
					GEngine->GetEngineSubsystem<UBeamBeamballMsApi>()->CPP_SetEdgegapLocation(UserSlot, RequestObject, FOnBeamballMsSetEdgegapLocationFullResponse::CreateLambda(
						                                                                          [OperationHandler, this](FBeamballMsSetEdgegapLocationFullResponse Event)
						                                                                          {
							                                                                          if (Event.State == EBeamFullResponseState::RS_Retrying)
								                                                                          return;

							                                                                          if (Event.State == RS_Success)
							                                                                          {
								                                                                          Runtime->RequestTrackerSystem->TriggerOperationSuccess(
									                                                                          OperationHandler, "Successfully updated location stat");
							                                                                          }
							                                                                          else
							                                                                          {
								                                                                          Runtime->RequestTrackerSystem->TriggerOperationError(
									                                                                          OperationHandler, "Error on updated location stat");
							                                                                          }
						                                                                          }), Ctx, RequestOperation, this);
				}
			});

		Request->ProcessRequest();

		return OperationHandler;
	}
};
