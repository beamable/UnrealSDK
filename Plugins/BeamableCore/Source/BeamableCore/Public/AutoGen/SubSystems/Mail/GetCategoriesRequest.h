
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/ListMailCategoriesResponse.h"

#include "GetCategoriesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCategoriesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetCategoriesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetCategoriesRequest* MakeGetCategoriesRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCategoriesSuccess, FBeamRequestContext, Context, UGetCategoriesRequest*, Request, UListMailCategoriesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCategoriesError, FBeamRequestContext, Context, UGetCategoriesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCategoriesComplete, FBeamRequestContext, Context, UGetCategoriesRequest*, Request);

using FGetCategoriesFullResponse = FBeamFullResponse<UGetCategoriesRequest*, UListMailCategoriesResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCategoriesFullResponse, FGetCategoriesFullResponse);
