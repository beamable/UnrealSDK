
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/InventoryView.h"

#include "GetInventoryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetInventoryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamGamerTag ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Scope", Category="Beam")
	FOptionalString Scope = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetInventoryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make GetInventory",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Scope,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetInventoryRequest* Make(FBeamGamerTag _ObjectId, FOptionalString _Scope, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetInventorySuccess, FBeamRequestContext, Context, UGetInventoryRequest*, Request, UInventoryView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetInventoryError, FBeamRequestContext, Context, UGetInventoryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetInventoryComplete, FBeamRequestContext, Context, UGetInventoryRequest*, Request);

using FGetInventoryFullResponse = FBeamFullResponse<UGetInventoryRequest*, UInventoryView*>;
DECLARE_DELEGATE_OneParam(FOnGetInventoryFullResponse, FGetInventoryFullResponse);
