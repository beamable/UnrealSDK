
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GroupSearchResponse.h"

#include "GetRecommendedRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRecommendedRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetRecommendedRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetRecommendedRequest* MakeGetRecommendedRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRecommendedSuccess, FBeamRequestContext, Context, UGetRecommendedRequest*, Request, UGroupSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRecommendedError, FBeamRequestContext, Context, UGetRecommendedRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRecommendedComplete, FBeamRequestContext, Context, UGetRecommendedRequest*, Request);

using FGetRecommendedFullResponse = FBeamFullResponse<UGetRecommendedRequest*, UGroupSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRecommendedFullResponse, FGetRecommendedFullResponse);
