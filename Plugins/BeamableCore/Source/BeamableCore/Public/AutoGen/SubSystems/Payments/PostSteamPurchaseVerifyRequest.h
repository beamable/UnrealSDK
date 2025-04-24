
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/VerifyPurchaseRequestBody.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PostSteamPurchaseVerifyRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostSteamPurchaseVerifyRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UVerifyPurchaseRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostSteamPurchaseVerifyRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PostSteamPurchaseVerify",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostSteamPurchaseVerifyRequest* Make(FString _Receipt, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSteamPurchaseVerifySuccess, FBeamRequestContext, Context, UPostSteamPurchaseVerifyRequest*, Request, UPaymentResultResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostSteamPurchaseVerifyError, FBeamRequestContext, Context, UPostSteamPurchaseVerifyRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostSteamPurchaseVerifyComplete, FBeamRequestContext, Context, UPostSteamPurchaseVerifyRequest*, Request);

using FPostSteamPurchaseVerifyFullResponse = FBeamFullResponse<UPostSteamPurchaseVerifyRequest*, UPaymentResultResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostSteamPurchaseVerifyFullResponse, FPostSteamPurchaseVerifyFullResponse);
