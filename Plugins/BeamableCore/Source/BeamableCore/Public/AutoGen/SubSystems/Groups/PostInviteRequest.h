
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GroupInvite.h"
#include "AutoGen/CommonResponse.h"

#include "PostInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UGroupInvite* Body;

	// Beam Base Request Declaration
	UPostInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_SubGroup,_bUseNewRewardsSystem,Outer"))
	static UPostInviteRequest* MakePostInviteRequest(int64 _ObjectId, int64 _GamerTag, FOptionalInt64 _SubGroup, FOptionalBool _bUseNewRewardsSystem, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInviteSuccess, FBeamRequestContext, Context, UPostInviteRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostInviteError, FBeamRequestContext, Context, UPostInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostInviteComplete, FBeamRequestContext, Context, UPostInviteRequest*, Request);

using FPostInviteFullResponse = FBeamFullResponse<UPostInviteRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostInviteFullResponse, FPostInviteFullResponse);
