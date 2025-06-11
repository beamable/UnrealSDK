
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/InventoryUpdateRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutInventoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutInventoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamGamerTag ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UInventoryUpdateRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutInventoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PutInventory",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bApplyVipBonus,_Transaction,_UpdateItems,_NewItems,_DeleteItems,_Currencies,_CurrencyProperties,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutInventoryRequest* Make(FBeamGamerTag _ObjectId, FOptionalBool _bApplyVipBonus, FOptionalString _Transaction, FOptionalArrayOfItemUpdateRequestBody _UpdateItems, FOptionalArrayOfItemCreateRequestBody _NewItems, FOptionalArrayOfItemDeleteRequestBody _DeleteItems, FOptionalMapOfInt64 _Currencies, FOptionalMapOfArrayOfCurrencyProperty _CurrencyProperties, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutInventorySuccess, FBeamRequestContext, Context, UPutInventoryRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutInventoryError, FBeamRequestContext, Context, UPutInventoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutInventoryComplete, FBeamRequestContext, Context, UPutInventoryRequest*, Request);

using FPutInventoryFullResponse = FBeamFullResponse<UPutInventoryRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutInventoryFullResponse, FPutInventoryFullResponse);
