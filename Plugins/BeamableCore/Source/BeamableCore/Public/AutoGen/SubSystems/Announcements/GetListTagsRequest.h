
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/ListTagsResponse.h"

#include "GetListTagsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetListTagsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag Name Filter")
	FOptionalString TagNameFilter;

	// Body Params
	

	// Beam Base Request Declaration
	UGetListTagsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_TagNameFilter,Outer"))
	static UGetListTagsRequest* MakeGetListTagsRequest(FOptionalString _TagNameFilter, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetListTagsSuccess, FBeamRequestContext, Context, UGetListTagsRequest*, Request, UListTagsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetListTagsError, FBeamRequestContext, Context, UGetListTagsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetListTagsComplete, FBeamRequestContext, Context, UGetListTagsRequest*, Request);

using FGetListTagsFullResponse = FBeamFullResponse<UGetListTagsRequest*, UListTagsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetListTagsFullResponse, FGetListTagsFullResponse);
