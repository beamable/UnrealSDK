
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/EndTransactionRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteTransactionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteTransactionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UEndTransactionRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteTransactionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Inventory", DisplayName="Beam - Make DeleteTransaction",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteTransactionRequest* Make(int64 _ObjectId, FString _Transaction, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTransactionSuccess, FBeamRequestContext, Context, UDeleteTransactionRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTransactionError, FBeamRequestContext, Context, UDeleteTransactionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteTransactionComplete, FBeamRequestContext, Context, UDeleteTransactionRequest*, Request);

using FDeleteTransactionFullResponse = FBeamFullResponse<UDeleteTransactionRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteTransactionFullResponse, FDeleteTransactionFullResponse);
