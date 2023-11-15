
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/MailSearchRequestBody.h"
#include "BeamableCore/Public/AutoGen/MailSearchResponse.h"

#include "ObjectMailPostSearchRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectMailPostSearchRequest : public UObject, public IBeamBaseRequestInterface
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
	UObjectMailPostSearchRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Mail", DisplayName="Beam - Make ObjectMailPostSearch",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectMailPostSearchRequest* Make(int64 _ObjectId, TArray<UMailSearchClause*> _Clauses, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostSearchSuccess, FBeamRequestContext, Context, UObjectMailPostSearchRequest*, Request, UMailSearchResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectMailPostSearchError, FBeamRequestContext, Context, UObjectMailPostSearchRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectMailPostSearchComplete, FBeamRequestContext, Context, UObjectMailPostSearchRequest*, Request);

using FObjectMailPostSearchFullResponse = FBeamFullResponse<UObjectMailPostSearchRequest*, UMailSearchResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectMailPostSearchFullResponse, FObjectMailPostSearchFullResponse);
