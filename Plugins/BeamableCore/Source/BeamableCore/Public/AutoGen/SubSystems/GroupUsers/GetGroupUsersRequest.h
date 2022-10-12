
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/GroupUser.h"

#include "GetGroupUsersRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetGroupUsersRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetGroupUsersRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UGetGroupUsersRequest* MakeGetGroupUsersRequest(int64 _ObjectId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGroupUsersSuccess, FBeamRequestContext, Context, UGetGroupUsersRequest*, Request, UGroupUser*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetGroupUsersError, FBeamRequestContext, Context, UGetGroupUsersRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetGroupUsersComplete, FBeamRequestContext, Context, UGetGroupUsersRequest*, Request);

using FGetGroupUsersFullResponse = FBeamFullResponse<UGetGroupUsersRequest*, UGroupUser*>;
DECLARE_DELEGATE_OneParam(FOnGetGroupUsersFullResponse, FGetGroupUsersFullResponse);
