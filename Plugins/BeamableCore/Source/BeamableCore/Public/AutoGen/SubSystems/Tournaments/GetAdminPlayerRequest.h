
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/AdminGetPlayerStatusResponse.h"

#include "GetAdminPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetAdminPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	int64 PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FOptionalString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FOptionalString ContentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Has Unclaimed Rewards")
	FOptionalBool bHasUnclaimedRewards;

	// Body Params
	

	// Beam Base Request Declaration
	UGetAdminPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_TournamentId,_ContentId,_bHasUnclaimedRewards,Outer"))
	static UGetAdminPlayerRequest* MakeGetAdminPlayerRequest(int64 _PlayerId, FOptionalString _TournamentId, FOptionalString _ContentId, FOptionalBool _bHasUnclaimedRewards, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminPlayerSuccess, FBeamRequestContext, Context, UGetAdminPlayerRequest*, Request, UAdminGetPlayerStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetAdminPlayerError, FBeamRequestContext, Context, UGetAdminPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAdminPlayerComplete, FBeamRequestContext, Context, UGetAdminPlayerRequest*, Request);

using FGetAdminPlayerFullResponse = FBeamFullResponse<UGetAdminPlayerRequest*, UAdminGetPlayerStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetAdminPlayerFullResponse, FGetAdminPlayerFullResponse);
