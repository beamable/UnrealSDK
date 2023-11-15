
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/TournamentClientView.h"

#include "ObjectTournamentsGetTournamentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectTournamentsGetTournamentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectTournamentsGetTournamentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Tournaments", DisplayName="Beam - Make ObjectTournamentsGetTournaments",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectTournamentsGetTournamentsRequest* Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectTournamentsGetTournamentsSuccess, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsRequest*, Request, UTournamentClientView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectTournamentsGetTournamentsError, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectTournamentsGetTournamentsComplete, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsRequest*, Request);

using FObjectTournamentsGetTournamentsFullResponse = FBeamFullResponse<UObjectTournamentsGetTournamentsRequest*, UTournamentClientView*>;
DECLARE_DELEGATE_OneParam(FOnObjectTournamentsGetTournamentsFullResponse, FObjectTournamentsGetTournamentsFullResponse);
