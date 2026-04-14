
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AuthV2DeviceIdAuthRequestBody.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"

#include "PostTokensDeviceIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTokensDeviceIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAuthV2DeviceIdAuthRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTokensDeviceIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make PostTokensDeviceId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_DeviceId,_Scope,_CustomerId,_RealmId,_Context,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTokensDeviceIdRequest* Make(FOptionalString _DeviceId, FOptionalString _Scope, FOptionalBeamCid _CustomerId, FOptionalBeamPid _RealmId, FOptionalAuthV2ContextInfo _Context, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensDeviceIdSuccess, FBeamRequestContext, Context, UPostTokensDeviceIdRequest*, Request, UAuthV2AuthResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTokensDeviceIdError, FBeamRequestContext, Context, UPostTokensDeviceIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTokensDeviceIdComplete, FBeamRequestContext, Context, UPostTokensDeviceIdRequest*, Request);

using FPostTokensDeviceIdFullResponse = FBeamFullResponse<UPostTokensDeviceIdRequest*, UAuthV2AuthResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTokensDeviceIdFullResponse, FPostTokensDeviceIdFullResponse);
