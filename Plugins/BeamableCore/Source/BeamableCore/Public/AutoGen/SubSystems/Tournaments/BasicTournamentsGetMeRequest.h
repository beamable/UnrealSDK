
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/GetPlayerStatusResponse.h"

#include "BasicTournamentsGetMeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicTournamentsGetMeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id", Category="Beam")
	FOptionalString TournamentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FOptionalString ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Unclaimed Rewards", Category="Beam")
	FOptionalBool bHasUnclaimedRewards = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicTournamentsGetMeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make BasicTournamentsGetMe",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_TournamentId,_ContentId,_bHasUnclaimedRewards,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicTournamentsGetMeRequest* Make(FOptionalString _TournamentId, FOptionalString _ContentId, FOptionalBool _bHasUnclaimedRewards, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetMeSuccess, FBeamRequestContext, Context, UBasicTournamentsGetMeRequest*, Request, UGetPlayerStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicTournamentsGetMeError, FBeamRequestContext, Context, UBasicTournamentsGetMeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicTournamentsGetMeComplete, FBeamRequestContext, Context, UBasicTournamentsGetMeRequest*, Request);

using FBasicTournamentsGetMeFullResponse = FBeamFullResponse<UBasicTournamentsGetMeRequest*, UGetPlayerStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicTournamentsGetMeFullResponse, FBasicTournamentsGetMeFullResponse);
