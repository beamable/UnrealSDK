
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/TournamentClientView.h"

#include "ObjectTournamentsGetTournamentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectTournamentsGetTournamentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectTournamentsGetTournamentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UObjectTournamentsGetTournamentsRequest* MakeObjectTournamentsGetTournamentsRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectTournamentsGetTournamentsSuccess, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsRequest*, Request, UTournamentClientView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectTournamentsGetTournamentsError, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectTournamentsGetTournamentsComplete, FBeamRequestContext, Context, UObjectTournamentsGetTournamentsRequest*, Request);

using FObjectTournamentsGetTournamentsFullResponse = FBeamFullResponse<UObjectTournamentsGetTournamentsRequest*, UTournamentClientView*>;
DECLARE_DELEGATE_OneParam(FOnObjectTournamentsGetTournamentsFullResponse, FObjectTournamentsGetTournamentsFullResponse);
