
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/MailSearchRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSearchResponse.h"

#include "ObjectMailPostSearchByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPostSearchByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UMailSearchRequestBody* Body = {};

	// Beam Base Request Declaration
	UObjectMailPostSearchByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make ObjectMailPostSearchByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectMailPostSearchByObjectIdRequest* Make(int64 _ObjectId, TArray<UMailSearchClause*> _Clauses, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostSearchByObjectIdSuccess, FBeamRequestContext, Context, UObjectMailPostSearchByObjectIdRequest*, Request, UMailSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostSearchByObjectIdError, FBeamRequestContext, Context, UObjectMailPostSearchByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPostSearchByObjectIdComplete, FBeamRequestContext, Context, UObjectMailPostSearchByObjectIdRequest*, Request);

using FObjectMailPostSearchByObjectIdFullResponse = FBeamFullResponse<UObjectMailPostSearchByObjectIdRequest*, UMailSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPostSearchByObjectIdFullResponse, FObjectMailPostSearchByObjectIdFullResponse);
