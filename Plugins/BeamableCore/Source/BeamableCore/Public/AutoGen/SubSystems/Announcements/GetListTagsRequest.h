
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/ListTagsResponse.h"

#include "GetListTagsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetListTagsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tag Name Filter", Category="Beam")
	FOptionalString TagNameFilter = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetListTagsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make GetListTags",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_TagNameFilter,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetListTagsRequest* Make(FOptionalString _TagNameFilter, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetListTagsSuccess, FBeamRequestContext, Context, UGetListTagsRequest*, Request, UListTagsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetListTagsError, FBeamRequestContext, Context, UGetListTagsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetListTagsComplete, FBeamRequestContext, Context, UGetListTagsRequest*, Request);

using FGetListTagsFullResponse = FBeamFullResponse<UGetListTagsRequest*, UListTagsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetListTagsFullResponse, FGetListTagsFullResponse);
