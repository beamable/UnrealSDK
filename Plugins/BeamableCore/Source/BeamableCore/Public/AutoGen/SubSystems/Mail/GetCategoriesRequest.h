
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ListMailCategoriesResponse.h"

#include "GetCategoriesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetCategoriesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetCategoriesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make GetCategories",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetCategoriesRequest* Make(int64 _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCategoriesSuccess, FBeamRequestContext, Context, UGetCategoriesRequest*, Request, UListMailCategoriesResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetCategoriesError, FBeamRequestContext, Context, UGetCategoriesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetCategoriesComplete, FBeamRequestContext, Context, UGetCategoriesRequest*, Request);

using FGetCategoriesFullResponse = FBeamFullResponse<UGetCategoriesRequest*, UListMailCategoriesResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetCategoriesFullResponse, FGetCategoriesFullResponse);
