
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/AuthV2LegacyAccessToken.h"

#include "GetTokensAccessRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTokensAccessRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token Id", Category="Beam")
	FString TokenId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Customer Id", Category="Beam")
	FOptionalString CustomerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Realm Id", Category="Beam")
	FOptionalString RealmId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetTokensAccessRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make GetTokensAccess",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_CustomerId,_RealmId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetTokensAccessRequest* Make(FString _TokenId, FOptionalString _CustomerId, FOptionalString _RealmId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokensAccessSuccess, FBeamRequestContext, Context, UGetTokensAccessRequest*, Request, UAuthV2LegacyAccessToken*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokensAccessError, FBeamRequestContext, Context, UGetTokensAccessRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTokensAccessComplete, FBeamRequestContext, Context, UGetTokensAccessRequest*, Request);

using FGetTokensAccessFullResponse = FBeamFullResponse<UGetTokensAccessRequest*, UAuthV2LegacyAccessToken*>;
DECLARE_DELEGATE_OneParam(FOnGetTokensAccessFullResponse, FGetTokensAccessFullResponse);
