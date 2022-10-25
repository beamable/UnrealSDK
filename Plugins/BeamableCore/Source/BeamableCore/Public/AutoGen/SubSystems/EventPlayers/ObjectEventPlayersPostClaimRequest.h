
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "AutoGen/EventClaimRequestBody.h"
#include "AutoGen/EventClaimResponse.h"

#include "ObjectEventPlayersPostClaimRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectEventPlayersPostClaimRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UEventClaimRequestBody* Body;

	// Beam Base Request Declaration
	UObjectEventPlayersPostClaimRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|EventPlayers", DisplayName="Beam - Make ObjectEventPlayersPostClaim",  meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UObjectEventPlayersPostClaimRequest* Make(int64 _ObjectId, FString _EventId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectEventPlayersPostClaimSuccess, FBeamRequestContext, Context, UObjectEventPlayersPostClaimRequest*, Request, UEventClaimResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectEventPlayersPostClaimError, FBeamRequestContext, Context, UObjectEventPlayersPostClaimRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectEventPlayersPostClaimComplete, FBeamRequestContext, Context, UObjectEventPlayersPostClaimRequest*, Request);

using FObjectEventPlayersPostClaimFullResponse = FBeamFullResponse<UObjectEventPlayersPostClaimRequest*, UEventClaimResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectEventPlayersPostClaimFullResponse, FObjectEventPlayersPostClaimFullResponse);
