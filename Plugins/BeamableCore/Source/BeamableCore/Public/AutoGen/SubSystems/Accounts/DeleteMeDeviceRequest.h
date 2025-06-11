
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/DeleteDevicesRequestBody.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#include "DeleteMeDeviceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMeDeviceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UDeleteDevicesRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteMeDeviceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteMeDevice",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_DeviceIds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteMeDeviceRequest* Make(FOptionalArrayOfString _DeviceIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeDeviceSuccess, FBeamRequestContext, Context, UDeleteMeDeviceRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeDeviceError, FBeamRequestContext, Context, UDeleteMeDeviceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMeDeviceComplete, FBeamRequestContext, Context, UDeleteMeDeviceRequest*, Request);

using FDeleteMeDeviceFullResponse = FBeamFullResponse<UDeleteMeDeviceRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMeDeviceFullResponse, FDeleteMeDeviceFullResponse);
