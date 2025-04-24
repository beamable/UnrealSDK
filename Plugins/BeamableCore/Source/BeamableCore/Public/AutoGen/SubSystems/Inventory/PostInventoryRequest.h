
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/InventoryQueryRequestBody.h"
#include "BeamableCore/Public/AutoGen/InventoryView.h"

#include "PostInventoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostInventoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamGamerTag ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UInventoryQueryRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostInventoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make PostInventory",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Scopes,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostInventoryRequest* Make(FBeamGamerTag _ObjectId, FOptionalArrayOfString _Scopes, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInventorySuccess, FBeamRequestContext, Context, UPostInventoryRequest*, Request, UInventoryView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInventoryError, FBeamRequestContext, Context, UPostInventoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostInventoryComplete, FBeamRequestContext, Context, UPostInventoryRequest*, Request);

using FPostInventoryFullResponse = FBeamFullResponse<UPostInventoryRequest*, UInventoryView*>;
DECLARE_DELEGATE_OneParam(FOnPostInventoryFullResponse, FPostInventoryFullResponse);
