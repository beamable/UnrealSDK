
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/MicroserviceSecretResponse.h"

#include "GetMicroserviceSecretRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMicroserviceSecretRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetMicroserviceSecretRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetMicroserviceSecret",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetMicroserviceSecretRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMicroserviceSecretSuccess, FBeamRequestContext, Context, UGetMicroserviceSecretRequest*, Request, UMicroserviceSecretResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMicroserviceSecretError, FBeamRequestContext, Context, UGetMicroserviceSecretRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetMicroserviceSecretComplete, FBeamRequestContext, Context, UGetMicroserviceSecretRequest*, Request);

using FGetMicroserviceSecretFullResponse = FBeamFullResponse<UGetMicroserviceSecretRequest*, UMicroserviceSecretResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetMicroserviceSecretFullResponse, FGetMicroserviceSecretFullResponse);
