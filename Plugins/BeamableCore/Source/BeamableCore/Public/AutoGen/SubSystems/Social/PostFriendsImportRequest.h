
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ImportFriendsRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostFriendsImportRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFriendsImportRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UImportFriendsRequestBody* Body;

	// Beam Base Request Declaration
	UPostFriendsImportRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostFriendsImportRequest* MakePostFriendsImportRequest(FString _Source, FString _Token, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsImportSuccess, FBeamRequestContext, Context, UPostFriendsImportRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsImportError, FBeamRequestContext, Context, UPostFriendsImportRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFriendsImportComplete, FBeamRequestContext, Context, UPostFriendsImportRequest*, Request);

using FPostFriendsImportFullResponse = FBeamFullResponse<UPostFriendsImportRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFriendsImportFullResponse, FPostFriendsImportFullResponse);
