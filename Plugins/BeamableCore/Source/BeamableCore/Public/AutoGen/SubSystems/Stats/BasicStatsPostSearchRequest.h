
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/StatsSearchRequestBody.h"
#include "BeamableCore/Public/AutoGen/StatsSearchResponse.h"

#include "BasicStatsPostSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicStatsPostSearchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatsSearchRequestBody* Body = {};

	// Beam Base Request Declaration
	UBasicStatsPostSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make BasicStatsPostSearch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Offset,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicStatsPostSearchRequest* Make(FString _Domain, FString _ObjectType, FString _Access, TArray<UStatsSearchCriteria*> _Criteria, FOptionalInt32 _Offset, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicStatsPostSearchSuccess, FBeamRequestContext, Context, UBasicStatsPostSearchRequest*, Request, UStatsSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicStatsPostSearchError, FBeamRequestContext, Context, UBasicStatsPostSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicStatsPostSearchComplete, FBeamRequestContext, Context, UBasicStatsPostSearchRequest*, Request);

using FBasicStatsPostSearchFullResponse = FBeamFullResponse<UBasicStatsPostSearchRequest*, UStatsSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicStatsPostSearchFullResponse, FBasicStatsPostSearchFullResponse);
