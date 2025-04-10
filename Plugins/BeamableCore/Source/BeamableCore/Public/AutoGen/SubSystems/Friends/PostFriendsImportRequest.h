
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ImportFriendsRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostFriendsImportRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostFriendsImportRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UImportFriendsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostFriendsImportRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make PostFriendsImport",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostFriendsImportRequest* Make(FString _Source, FString _Token, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsImportSuccess, FBeamRequestContext, Context, UPostFriendsImportRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostFriendsImportError, FBeamRequestContext, Context, UPostFriendsImportRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostFriendsImportComplete, FBeamRequestContext, Context, UPostFriendsImportRequest*, Request);

using FPostFriendsImportFullResponse = FBeamFullResponse<UPostFriendsImportRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostFriendsImportFullResponse, FPostFriendsImportFullResponse);
