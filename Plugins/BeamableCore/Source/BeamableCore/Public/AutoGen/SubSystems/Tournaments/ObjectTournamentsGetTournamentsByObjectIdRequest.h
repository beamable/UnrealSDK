
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/TournamentClientView.h"

#include "ObjectTournamentsGetTournamentsByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectTournamentsGetTournamentsByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectTournamentsGetTournamentsByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make ObjectTournamentsGetTournamentsByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectTournamentsGetTournamentsByObjectIdRequest* Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectTournamentsGetTournamentsByObjectIdSuccess, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsByObjectIdRequest*, Request, UTournamentClientView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectTournamentsGetTournamentsByObjectIdError, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectTournamentsGetTournamentsByObjectIdComplete, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsByObjectIdRequest*, Request);

using FObjectTournamentsGetTournamentsByObjectIdFullResponse = FBeamFullResponse<UObjectTournamentsGetTournamentsByObjectIdRequest*, UTournamentClientView*>;
DECLARE_DELEGATE_OneParam(FOnObjectTournamentsGetTournamentsByObjectIdFullResponse, FObjectTournamentsGetTournamentsByObjectIdFullResponse);
