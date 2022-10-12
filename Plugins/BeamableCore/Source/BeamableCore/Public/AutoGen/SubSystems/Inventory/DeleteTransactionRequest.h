
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/EndTransactionRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteTransactionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteTransactionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UEndTransactionRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteTransactionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteTransactionRequest* MakeDeleteTransactionRequest(int64 _ObjectId, FString _Transaction, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTransactionSuccess, FBeamRequestContext, Context, UDeleteTransactionRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTransactionError, FBeamRequestContext, Context, UDeleteTransactionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteTransactionComplete, FBeamRequestContext, Context, UDeleteTransactionRequest*, Request);

using FDeleteTransactionFullResponse = FBeamFullResponse<UDeleteTransactionRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteTransactionFullResponse, FDeleteTransactionFullResponse);
