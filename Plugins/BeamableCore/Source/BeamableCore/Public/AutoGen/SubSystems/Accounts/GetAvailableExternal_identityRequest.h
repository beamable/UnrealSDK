
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/AccountAvailableResponse.h"

#include "GetAvailableExternal_identityRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAvailableExternal_identityRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Service", Category="Beam")
	FString ProviderService;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="User Id", Category="Beam")
	FString UserId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Namespace", Category="Beam")
	FOptionalString ProviderNamespace;

	// Body Params
	

	// Beam Base Request Declaration
	UGetAvailableExternal_identityRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Accounts", DisplayName="Beam - Make GetAvailableExternal_identity",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ProviderNamespace,RequestOwner"))
	static UGetAvailableExternal_identityRequest* Make(FString _ProviderService, FString _UserId, FOptionalString _ProviderNamespace, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableExternal_identitySuccess, FBeamRequestContext, Context, UGetAvailableExternal_identityRequest*, Request, UAccountAvailableResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAvailableExternal_identityError, FBeamRequestContext, Context, UGetAvailableExternal_identityRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableExternal_identityComplete, FBeamRequestContext, Context, UGetAvailableExternal_identityRequest*, Request);

using FGetAvailableExternal_identityFullResponse = FBeamFullResponse<UGetAvailableExternal_identityRequest*, UAccountAvailableResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAvailableExternal_identityFullResponse, FGetAvailableExternal_identityFullResponse);
