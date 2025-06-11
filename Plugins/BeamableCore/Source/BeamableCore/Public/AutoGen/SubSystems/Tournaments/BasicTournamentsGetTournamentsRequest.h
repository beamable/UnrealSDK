
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/TournamentQueryResponse.h"

#include "BasicTournamentsGetTournamentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicTournamentsGetTournamentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Running", Category="Beam")
	FOptionalBool bIsRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FOptionalString ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle", Category="Beam")
	FOptionalInt32 Cycle = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicTournamentsGetTournamentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make BasicTournamentsGetTournaments",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bIsRunning,_ContentId,_Cycle,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicTournamentsGetTournamentsRequest* Make(FOptionalBool _bIsRunning, FOptionalString _ContentId, FOptionalInt32 _Cycle, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetTournamentsSuccess, FBeamRequestContext, Context, UBasicTournamentsGetTournamentsRequest*, Request, UTournamentQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetTournamentsError, FBeamRequestContext, Context, UBasicTournamentsGetTournamentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicTournamentsGetTournamentsComplete, FBeamRequestContext, Context, UBasicTournamentsGetTournamentsRequest*, Request);

using FBasicTournamentsGetTournamentsFullResponse = FBeamFullResponse<UBasicTournamentsGetTournamentsRequest*, UTournamentQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicTournamentsGetTournamentsFullResponse, FBasicTournamentsGetTournamentsFullResponse);
