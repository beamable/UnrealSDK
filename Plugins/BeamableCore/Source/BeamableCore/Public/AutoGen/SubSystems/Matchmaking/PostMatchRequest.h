
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/MatchUpdate.h"

#include "PostMatchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostMatchRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UPostMatchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Matchmaking", DisplayName="Beam - Make PostMatch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner"))
	static UPostMatchRequest* Make(int64 _ObjectId, UObject* RequestOwner);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMatchSuccess, FBeamRequestContext, Context, UPostMatchRequest*, Request, UMatchUpdate*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostMatchError, FBeamRequestContext, Context, UPostMatchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostMatchComplete, FBeamRequestContext, Context, UPostMatchRequest*, Request);

using FPostMatchFullResponse = FBeamFullResponse<UPostMatchRequest*, UMatchUpdate*>;
DECLARE_DELEGATE_OneParam(FOnPostMatchFullResponse, FPostMatchFullResponse);
