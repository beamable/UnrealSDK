
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/MatchUpdate.h"

#include "PostMatchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMatchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPostMatchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostMatchRequest* MakePostMatchRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMatchSuccess, FBeamRequestContext, Context, UPostMatchRequest*, Request, UMatchUpdate*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMatchError, FBeamRequestContext, Context, UPostMatchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMatchComplete, FBeamRequestContext, Context, UPostMatchRequest*, Request);

using FPostMatchFullResponse = FBeamFullResponse<UPostMatchRequest*, UMatchUpdate*>;
DECLARE_DELEGATE_OneParam(FOnPostMatchFullResponse, FPostMatchFullResponse);
