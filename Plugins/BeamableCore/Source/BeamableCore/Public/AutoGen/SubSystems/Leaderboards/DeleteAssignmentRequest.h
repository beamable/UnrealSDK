
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaderboardRemoveCacheEntryRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteAssignmentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAssignmentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	ULeaderboardRemoveCacheEntryRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteAssignmentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make DeleteAssignment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteAssignmentRequest* Make(FString _ObjectId, int64 _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAssignmentSuccess, FBeamRequestContext, Context, UDeleteAssignmentRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAssignmentError, FBeamRequestContext, Context, UDeleteAssignmentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteAssignmentComplete, FBeamRequestContext, Context, UDeleteAssignmentRequest*, Request);

using FDeleteAssignmentFullResponse = FBeamFullResponse<UDeleteAssignmentRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteAssignmentFullResponse, FDeleteAssignmentFullResponse);
