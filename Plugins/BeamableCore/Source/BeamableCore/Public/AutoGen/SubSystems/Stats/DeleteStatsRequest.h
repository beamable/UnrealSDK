
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/StatRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "DeleteStatsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteStatsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamStatsType ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteStatsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make DeleteStats",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Stats,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteStatsRequest* Make(FBeamStatsType _ObjectId, FOptionalString _Stats, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatsSuccess, FBeamRequestContext, Context, UDeleteStatsRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteStatsError, FBeamRequestContext, Context, UDeleteStatsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteStatsComplete, FBeamRequestContext, Context, UDeleteStatsRequest*, Request);

using FDeleteStatsFullResponse = FBeamFullResponse<UDeleteStatsRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteStatsFullResponse, FDeleteStatsFullResponse);
