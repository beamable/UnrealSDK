
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Token.h"

#include "GetTokenRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTokenRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Token", Category="Beam")
	FString Token = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetTokenRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make GetToken",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetTokenRequest* Make(FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenSuccess, FBeamRequestContext, Context, UGetTokenRequest*, Request, UToken*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTokenError, FBeamRequestContext, Context, UGetTokenRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTokenComplete, FBeamRequestContext, Context, UGetTokenRequest*, Request);

using FGetTokenFullResponse = FBeamFullResponse<UGetTokenRequest*, UToken*>;
DECLARE_DELEGATE_OneParam(FOnGetTokenFullResponse, FGetTokenFullResponse);
