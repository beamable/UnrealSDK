
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/EventClaimRequestBody.h"
#include "BeamableCore/Public/AutoGen/EventClaimResponse.h"

#include "ObjectEventPlayersPostClaimByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectEventPlayersPostClaimByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UEventClaimRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectEventPlayersPostClaimByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|EventPlayers|Utils|Make/Break", DisplayName="Make ObjectEventPlayersPostClaimByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectEventPlayersPostClaimByObjectIdRequest* Make(int64 _ObjectId, FString _EventId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectEventPlayersPostClaimByObjectIdSuccess, FBeamRequestContext, Context, UObjectEventPlayersPostClaimByObjectIdRequest*, Request, UEventClaimResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectEventPlayersPostClaimByObjectIdError, FBeamRequestContext, Context, UObjectEventPlayersPostClaimByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectEventPlayersPostClaimByObjectIdComplete, FBeamRequestContext, Context, UObjectEventPlayersPostClaimByObjectIdRequest*, Request);

using FObjectEventPlayersPostClaimByObjectIdFullResponse = FBeamFullResponse<UObjectEventPlayersPostClaimByObjectIdRequest*, UEventClaimResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectEventPlayersPostClaimByObjectIdFullResponse, FObjectEventPlayersPostClaimByObjectIdFullResponse);
