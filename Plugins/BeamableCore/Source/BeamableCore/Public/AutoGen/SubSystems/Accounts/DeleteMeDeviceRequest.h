
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/DeleteDevicesRequestBody.h"
#include "AutoGen/AccountPlayerView.h"

#include "DeleteMeDeviceRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteMeDeviceRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UDeleteDevicesRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteMeDeviceRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_DeviceIds,Outer"))
	static UDeleteMeDeviceRequest* MakeDeleteMeDeviceRequest(FOptionalArrayOfString _DeviceIds, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeDeviceSuccess, FBeamRequestContext, Context, UDeleteMeDeviceRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteMeDeviceError, FBeamRequestContext, Context, UDeleteMeDeviceRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteMeDeviceComplete, FBeamRequestContext, Context, UDeleteMeDeviceRequest*, Request);

using FDeleteMeDeviceFullResponse = FBeamFullResponse<UDeleteMeDeviceRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnDeleteMeDeviceFullResponse, FDeleteMeDeviceFullResponse);
