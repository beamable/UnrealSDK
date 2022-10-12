
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/TransferRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutTransferRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutTransferRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UTransferRequestBody* Body;

	// Beam Base Request Declaration
	UPutTransferRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Transaction,_Currencies,Outer"))
	static UPutTransferRequest* MakePutTransferRequest(int64 _ObjectId, FOptionalString _Transaction, int64 _RecipientPlayer, FOptionalMapOfInt64 _Currencies, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTransferSuccess, FBeamRequestContext, Context, UPutTransferRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutTransferError, FBeamRequestContext, Context, UPutTransferRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutTransferComplete, FBeamRequestContext, Context, UPutTransferRequest*, Request);

using FPutTransferFullResponse = FBeamFullResponse<UPutTransferRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutTransferFullResponse, FPutTransferFullResponse);
