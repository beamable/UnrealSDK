
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/StatsSearchRequestBody.h"
#include "AutoGen/StatsSearchResponse.h"

#include "BasicStatsPostSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicStatsPostSearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UStatsSearchRequestBody* Body;

	// Beam Base Request Declaration
	UBasicStatsPostSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UBasicStatsPostSearchRequest* MakeBasicStatsPostSearchRequest(FString _Domain, FString _Access, FString _ObjectType, TArray<UStatsSearchCriteria*> _Criteria, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicStatsPostSearchSuccess, FBeamRequestContext, Context, UBasicStatsPostSearchRequest*, Request, UStatsSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicStatsPostSearchError, FBeamRequestContext, Context, UBasicStatsPostSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicStatsPostSearchComplete, FBeamRequestContext, Context, UBasicStatsPostSearchRequest*, Request);

using FBasicStatsPostSearchFullResponse = FBeamFullResponse<UBasicStatsPostSearchRequest*, UStatsSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicStatsPostSearchFullResponse, FBasicStatsPostSearchFullResponse);
