
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LeaderboardRemoveCacheEntryRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "DeleteAssignmentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteAssignmentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	ULeaderboardRemoveCacheEntryRequestBody* Body;

	// Beam Base Request Declaration
	UDeleteAssignmentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UDeleteAssignmentRequest* MakeDeleteAssignmentRequest(FString _ObjectId, int64 _PlayerId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAssignmentSuccess, FBeamRequestContext, Context, UDeleteAssignmentRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteAssignmentError, FBeamRequestContext, Context, UDeleteAssignmentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteAssignmentComplete, FBeamRequestContext, Context, UDeleteAssignmentRequest*, Request);

using FDeleteAssignmentFullResponse = FBeamFullResponse<UDeleteAssignmentRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteAssignmentFullResponse, FDeleteAssignmentFullResponse);
