
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusResponse.h"

#include "GetAdminPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAdminPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	int64 PlayerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id", Category="Beam")
	FOptionalString TournamentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FOptionalString ContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Unclaimed Rewards", Category="Beam")
	FOptionalBool bHasUnclaimedRewards = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetAdminPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetAdminPlayer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_TournamentId,_ContentId,_bHasUnclaimedRewards,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetAdminPlayerRequest* Make(int64 _PlayerId, FOptionalString _TournamentId, FOptionalString _ContentId, FOptionalBool _bHasUnclaimedRewards, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminPlayerSuccess, FBeamRequestContext, Context, UGetAdminPlayerRequest*, Request, UAdminGetPlayerStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminPlayerError, FBeamRequestContext, Context, UGetAdminPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAdminPlayerComplete, FBeamRequestContext, Context, UGetAdminPlayerRequest*, Request);

using FGetAdminPlayerFullResponse = FBeamFullResponse<UGetAdminPlayerRequest*, UAdminGetPlayerStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAdminPlayerFullResponse, FGetAdminPlayerFullResponse);
