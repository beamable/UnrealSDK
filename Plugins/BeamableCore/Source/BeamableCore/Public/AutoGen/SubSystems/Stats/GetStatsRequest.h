
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/StatsResponse.h"

#include "GetStatsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetStatsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamStatsType ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats", Category="Beam")
	FOptionalString Stats = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetStatsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make GetStats",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Stats,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetStatsRequest* Make(FBeamStatsType _ObjectId, FOptionalString _Stats, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStatsSuccess, FBeamRequestContext, Context, UGetStatsRequest*, Request, UStatsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetStatsError, FBeamRequestContext, Context, UGetStatsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetStatsComplete, FBeamRequestContext, Context, UGetStatsRequest*, Request);

using FGetStatsFullResponse = FBeamFullResponse<UGetStatsRequest*, UStatsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetStatsFullResponse, FGetStatsFullResponse);
