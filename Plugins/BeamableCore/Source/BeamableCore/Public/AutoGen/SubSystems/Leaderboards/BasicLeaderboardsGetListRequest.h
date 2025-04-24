
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/LeaderboardListResponse.h"

#include "BasicLeaderboardsGetListRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicLeaderboardsGetListRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Skip", Category="Beam")
	FOptionalInt32 Skip = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Prefix", Category="Beam")
	FOptionalString Prefix = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Include Partitions", Category="Beam")
	FOptionalBool bIncludePartitions = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicLeaderboardsGetListRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make BasicLeaderboardsGetList",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Skip,_Limit,_Prefix,_bIncludePartitions,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicLeaderboardsGetListRequest* Make(FOptionalInt32 _Skip, FOptionalInt32 _Limit, FOptionalString _Prefix, FOptionalBool _bIncludePartitions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetListSuccess, FBeamRequestContext, Context, UBasicLeaderboardsGetListRequest*, Request, ULeaderboardListResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetListError, FBeamRequestContext, Context, UBasicLeaderboardsGetListRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicLeaderboardsGetListComplete, FBeamRequestContext, Context, UBasicLeaderboardsGetListRequest*, Request);

using FBasicLeaderboardsGetListFullResponse = FBeamFullResponse<UBasicLeaderboardsGetListRequest*, ULeaderboardListResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicLeaderboardsGetListFullResponse, FBasicLeaderboardsGetListFullResponse);
