
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/InventoryQueryRequestBody.h"
#include "AutoGen/InventoryView.h"

#include "PostInventoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostInventoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UInventoryQueryRequestBody* Body;

	// Beam Base Request Declaration
	UPostInventoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Scopes,Outer"))
	static UPostInventoryRequest* MakePostInventoryRequest(int64 _ObjectId, FOptionalArrayOfString _Scopes, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInventorySuccess, FBeamRequestContext, Context, UPostInventoryRequest*, Request, UInventoryView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInventoryError, FBeamRequestContext, Context, UPostInventoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostInventoryComplete, FBeamRequestContext, Context, UPostInventoryRequest*, Request);

using FPostInventoryFullResponse = FBeamFullResponse<UPostInventoryRequest*, UInventoryView*>;
DECLARE_DELEGATE_OneParam(FOnPostInventoryFullResponse, FPostInventoryFullResponse);
