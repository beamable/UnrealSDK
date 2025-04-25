
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionInfo.h"

#include "GetPartitionRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPartitionRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	int64 PlayerId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetPartitionRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make GetPartition",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetPartitionRequest* Make(FString _ObjectId, int64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPartitionSuccess, FBeamRequestContext, Context, UGetPartitionRequest*, Request, ULeaderboardPartitionInfo*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPartitionError, FBeamRequestContext, Context, UGetPartitionRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPartitionComplete, FBeamRequestContext, Context, UGetPartitionRequest*, Request);

using FGetPartitionFullResponse = FBeamFullResponse<UGetPartitionRequest*, ULeaderboardPartitionInfo*>;
DECLARE_DELEGATE_OneParam(FOnGetPartitionFullResponse, FGetPartitionFullResponse);
