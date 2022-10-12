
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/InventoryView.h"

#include "GetInventoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetInventoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope")
	FOptionalString Scope;

	// Body Params
	

	// Beam Base Request Declaration
	UGetInventoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Scope,Outer"))
	static UGetInventoryRequest* MakeGetInventoryRequest(int64 _ObjectId, FOptionalString _Scope, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetInventorySuccess, FBeamRequestContext, Context, UGetInventoryRequest*, Request, UInventoryView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetInventoryError, FBeamRequestContext, Context, UGetInventoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetInventoryComplete, FBeamRequestContext, Context, UGetInventoryRequest*, Request);

using FGetInventoryFullResponse = FBeamFullResponse<UGetInventoryRequest*, UInventoryView*>;
DECLARE_DELEGATE_OneParam(FOnGetInventoryFullResponse, FGetInventoryFullResponse);
