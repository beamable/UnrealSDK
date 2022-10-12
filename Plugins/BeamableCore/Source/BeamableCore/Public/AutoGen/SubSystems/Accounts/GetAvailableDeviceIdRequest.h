
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/AccountAvailableResponse.h"

#include "GetAvailableDeviceIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailableDeviceIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Device Id")
	FString DeviceId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailableDeviceIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetAvailableDeviceIdRequest* MakeGetAvailableDeviceIdRequest(FString _DeviceId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableDeviceIdSuccess, FBeamRequestContext, Context, UGetAvailableDeviceIdRequest*, Request, UAccountAvailableResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableDeviceIdError, FBeamRequestContext, Context, UGetAvailableDeviceIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableDeviceIdComplete, FBeamRequestContext, Context, UGetAvailableDeviceIdRequest*, Request);

using FGetAvailableDeviceIdFullResponse = FBeamFullResponse<UGetAvailableDeviceIdRequest*, UAccountAvailableResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailableDeviceIdFullResponse, FGetAvailableDeviceIdFullResponse);
