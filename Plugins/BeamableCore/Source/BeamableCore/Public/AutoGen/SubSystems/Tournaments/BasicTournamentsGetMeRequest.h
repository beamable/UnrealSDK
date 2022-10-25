
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/GetPlayerStatusResponse.h"

#include "BasicTournamentsGetMeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicTournamentsGetMeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id", Category="Beam")
	FOptionalString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FOptionalString ContentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Unclaimed Rewards", Category="Beam")
	FOptionalBool bHasUnclaimedRewards;

	// Body Params
	

	// Beam Base Request Declaration
	UBasicTournamentsGetMeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Tournaments", DisplayName="Beam - Make BasicTournamentsGetMe",  meta=(DefaultToSelf="Outer", AdvancedDisplay="_TournamentId,_ContentId,_bHasUnclaimedRewards,Outer"))
	static UBasicTournamentsGetMeRequest* Make(FOptionalString _TournamentId, FOptionalString _ContentId, FOptionalBool _bHasUnclaimedRewards, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetMeSuccess, FBeamRequestContext, Context, UBasicTournamentsGetMeRequest*, Request, UGetPlayerStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetMeError, FBeamRequestContext, Context, UBasicTournamentsGetMeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicTournamentsGetMeComplete, FBeamRequestContext, Context, UBasicTournamentsGetMeRequest*, Request);

using FBasicTournamentsGetMeFullResponse = FBeamFullResponse<UBasicTournamentsGetMeRequest*, UGetPlayerStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicTournamentsGetMeFullResponse, FBasicTournamentsGetMeFullResponse);
