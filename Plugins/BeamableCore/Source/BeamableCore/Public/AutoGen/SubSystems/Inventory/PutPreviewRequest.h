
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/InventoryUpdateRequestBody.h"
#include "AutoGen/PreviewVipBonusResponse.h"

#include "PutPreviewRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPreviewRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UInventoryUpdateRequestBody* Body;

	// Beam Base Request Declaration
	UPutPreviewRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Currencies,_CurrencyProperties,_bApplyVipBonus,_UpdateItems,_NewItems,_Transaction,_DeleteItems,Outer"))
	static UPutPreviewRequest* MakePutPreviewRequest(int64 _ObjectId, FOptionalMapOfInt64 _Currencies, bool _bEmpty, FOptionalMapOfArrayOfCurrencyProperty _CurrencyProperties, TArray<FString> _CurrencyContentIds, FOptionalBool _bApplyVipBonus, TArray<FString> _ItemContentIds, FOptionalArrayOfItemUpdateRequestBody _UpdateItems, FOptionalArrayOfItemCreateRequestBody _NewItems, FOptionalString _Transaction, FOptionalArrayOfItemDeleteRequestBody _DeleteItems, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPreviewSuccess, FBeamRequestContext, Context, UPutPreviewRequest*, Request, UPreviewVipBonusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPreviewError, FBeamRequestContext, Context, UPutPreviewRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPreviewComplete, FBeamRequestContext, Context, UPutPreviewRequest*, Request);

using FPutPreviewFullResponse = FBeamFullResponse<UPutPreviewRequest*, UPreviewVipBonusResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutPreviewFullResponse, FPutPreviewFullResponse);
