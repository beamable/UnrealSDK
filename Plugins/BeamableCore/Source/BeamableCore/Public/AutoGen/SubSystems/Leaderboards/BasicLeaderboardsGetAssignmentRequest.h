
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/LeaderboardAssignmentInfo.h"

#include "BasicLeaderboardsGetAssignmentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicLeaderboardsGetAssignmentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Board Id")
	FString BoardId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Join Board")
	FOptionalBool bJoinBoard;

	// Body Params
	

	// Beam Base Request Declaration
	UBasicLeaderboardsGetAssignmentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_bJoinBoard,Outer"))
	static UBasicLeaderboardsGetAssignmentRequest* MakeBasicLeaderboardsGetAssignmentRequest(FString _BoardId, FOptionalBool _bJoinBoard, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetAssignmentSuccess, FBeamRequestContext, Context, UBasicLeaderboardsGetAssignmentRequest*, Request, ULeaderboardAssignmentInfo*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetAssignmentError, FBeamRequestContext, Context, UBasicLeaderboardsGetAssignmentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicLeaderboardsGetAssignmentComplete, FBeamRequestContext, Context, UBasicLeaderboardsGetAssignmentRequest*, Request);

using FBasicLeaderboardsGetAssignmentFullResponse = FBeamFullResponse<UBasicLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>;
DECLARE_DELEGATE_OneParam(FOnBasicLeaderboardsGetAssignmentFullResponse, FBasicLeaderboardsGetAssignmentFullResponse);
