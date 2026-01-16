
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/VerifyReceiptRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"

#include "PostReceiptRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostReceiptRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UVerifyReceiptRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostReceiptRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make PostReceipt",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Provider,_Receipt,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostReceiptRequest* Make(FOptionalString _Provider, FOptionalString _Receipt, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostReceiptSuccess, FBeamRequestContext, Context, UPostReceiptRequest*, Request, UEmptyMessage*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostReceiptError, FBeamRequestContext, Context, UPostReceiptRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostReceiptComplete, FBeamRequestContext, Context, UPostReceiptRequest*, Request);

using FPostReceiptFullResponse = FBeamFullResponse<UPostReceiptRequest*, UEmptyMessage*>;
DECLARE_DELEGATE_OneParam(FOnPostReceiptFullResponse, FPostReceiptFullResponse);
