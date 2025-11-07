
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#include "BasicRealmsGetConfigRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicRealmsGetConfigRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UBasicRealmsGetConfigRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make BasicRealmsGetConfig",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicRealmsGetConfigRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetConfigSuccess, FBeamRequestContext, Context, UBasicRealmsGetConfigRequest*, Request, URealmConfigResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicRealmsGetConfigError, FBeamRequestContext, Context, UBasicRealmsGetConfigRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicRealmsGetConfigComplete, FBeamRequestContext, Context, UBasicRealmsGetConfigRequest*, Request);

using FBasicRealmsGetConfigFullResponse = FBeamFullResponse<UBasicRealmsGetConfigRequest*, URealmConfigResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicRealmsGetConfigFullResponse, FBasicRealmsGetConfigFullResponse);
